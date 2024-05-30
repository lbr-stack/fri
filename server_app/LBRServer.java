package lbr_fri_ros2;
 
import static com.kuka.roboticsAPI.motionModel.BasicMotions.positionHold;
 
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import javax.inject.Inject;
import java.util.Arrays;
 
import com.kuka.roboticsAPI.applicationModel.RoboticsAPIApplication;
import com.kuka.sensitivity.LBR;
import com.kuka.sensitivity.controlmode.CartesianImpedanceControlMode;
import com.kuka.sensitivity.controlmode.JointImpedanceControlMode;
import com.kuka.roboticsAPI.uiModel.ApplicationDialogType;
import com.kuka.roboticsAPI.uiModel.IApplicationUI;
import com.kuka.roboticsAPI.motionModel.controlModeModel.*;
//import com.kuka.fri.FRIChannelInformation;
//import com.kuka.fri.FRIConfiguration;
//import com.kuka.fri.FRISession;
//import com.kuka.fri.IFRISessionListener;
//import com.kuka.fri.FRIJointOverlay;
//import com.kuka.fri.common.ClientCommandMode;
import com.kuka.fri.api.monitoring.IFriChannelInformation;
import com.kuka.fri.api.monitoring.IFriConfiguration;
import com.kuka.fri.api.monitoring.IFriMonitoring;
import com.kuka.fri.api.monitoring.IFriSession;
import com.kuka.fri.api.monitoring.IFriSessionListener;
 
import com.kuka.fri.api.commanding.IFriJointOverlay;
import com.kuka.fri.api.commanding.EClientCommandMode;
import com.kuka.fri.api.commanding.IFriCommanding;
 
 
public class LBRServer extends RoboticsAPIApplication {
  // members
  @Inject
  private LBR lbr_;
  @Inject
  private IApplicationUI applicationUi;
 
  // control mode
  private enum CONTROL_MODE {
    POSITION_CONTROL,
    JOINT_IMPEDANCE_CONTROL,
    CARTESIAN_IMPEDANCE_CONTROL;
  }
 
  // convert enum to string array, see
  // https://stackoverflow.com/questions/13783295/getting-all-names-in-an-enum-as-a-string
  public static String[] getNames(Class<? extends Enum<?>> e) {
    return Arrays.toString(e.getEnumConstants()).replaceAll("^.|.$", "").split(", ");
  }
 
  // FRI parameters
  private String client_name_;
  private String[] client_names_ = { "172.31.1.148", "192.170.10.1" };
  private int send_period_;
  private String[] send_periods_ = { "1", "2", "5", "10" }; // send period in ms
 
  private IFriConfiguration fri_configuration_;
  private IFriSession fri_session_;
  private IFriJointOverlay fri_overlay_;
 
  private AbstractMotionControlMode control_mode_;
  private String[] control_modes_ = getNames(CONTROL_MODE.class);
  private EClientCommandMode command_mode_;
  private String[] command_modes_ = getNames(EClientCommandMode.class);
 
  // methods
  public void request_user_config() {
    // send period
    int selectedButtonIndex = applicationUi.displayModalDialog(
        ApplicationDialogType.QUESTION,
        "Select the desired FRI send period [ms]:",
        send_periods_);
    send_period_ = Integer.valueOf(send_periods_[selectedButtonIndex]);
    getLogger().info("Send period set to: " + send_period_);
    // remote IP address
    selectedButtonIndex = applicationUi.displayModalDialog(
        ApplicationDialogType.QUESTION,
        "Select your remote IP address:",
        client_names_);
    client_name_ = client_names_[selectedButtonIndex];
    getLogger().info("Remote address set to: " + client_name_);
 
    // control mode
    selectedButtonIndex = applicationUi.displayModalDialog(
        ApplicationDialogType.QUESTION,
        "Select the desired FRI control mode: ",
        control_modes_);
 
    CONTROL_MODE control_mode = CONTROL_MODE.values()[selectedButtonIndex];
    switch (control_mode) {
      case POSITION_CONTROL:
        control_mode_ = new PositionControlMode();
        break;
      case JOINT_IMPEDANCE_CONTROL:
        control_mode_ = new JointImpedanceControlMode(200, 200, 200, 200, 200, 200, 200);
        break;
      case CARTESIAN_IMPEDANCE_CONTROL:
        control_mode_ = new CartesianImpedanceControlMode();
        break;
    }
    getLogger().info("Control mode set to: " + control_mode.name());
    // command mode
    selectedButtonIndex = applicationUi.displayModalDialog(
        ApplicationDialogType.QUESTION,
        "Select the desired FRI client command mode: ",
        command_modes_);
    command_mode_ = EClientCommandMode.values()[selectedButtonIndex];
    getLogger().info("Client command mode set to: " + command_mode_.name());
  }
 
  public void configure_fri() {
    IFriMonitoring friMonitoring = lbr_.getCapability(IFriMonitoring.class);
    IFriCommanding friCommanding =lbr_.getCapability(IFriCommanding.class);
    fri_configuration_ = friMonitoring.createFriConfiguration(lbr_, client_name_);
    fri_configuration_.setSendPeriodMilliSec(send_period_);
    getLogger().info("Creating FRI connection to " + fri_configuration_.getHostName());
    getLogger().info(
        "SendPeriod: " + fri_configuration_.getSendPeriodMilliSec() + "ms |"
            + " ReceiveMultiplier: " + fri_configuration_.getReceiveMultiplier());
    fri_session_ = friMonitoring.createFriSession(fri_configuration_);
    fri_overlay_ = friCommanding.createJointOverlay(fri_session_, command_mode_);
    IFriSessionListener listener = new IFriSessionListener(){
      @Override
      public void onFriSessionStateChanged(IFriChannelInformation friChannelInformation) {
        getLogger().info("Session State change " + friChannelInformation.getFriSessionState().toString());
      }
 
      @Override
      public void onFriConnectionQualityChanged(IFriChannelInformation friChannelInformation) {
        getLogger().info("Quality change signalled " + friChannelInformation.getQuality());
        getLogger().info("Jitter " + friChannelInformation.getJitter());
        getLogger().info("Latency " + friChannelInformation.getLatency());
      }
    };
    fri_session_.addFriSessionListener(listener);
    // try to connect
    try {
      fri_session_.await(10, TimeUnit.SECONDS);
    } catch (final TimeoutException e) {
      getLogger().error(e.getLocalizedMessage());
      return;
    }
    getLogger().info("FRI connection established.");
  }
 
  @Override
  public void initialize() {
    // set FRI parameters
    request_user_config();
    // configure the FRI
    configure_fri();
  }
 
  @Override
  public void run() {
    // run the FRI
    lbr_.getFlange().move(positionHold(control_mode_, -1, TimeUnit.SECONDS).addMotionOverlay(fri_overlay_));
    return;
  }
 
  @Override
  public void dispose() {
    getLogger().info("Close connection to client");
 
    if (null != fri_session_) {
      fri_session_.close();
    }
  }
}