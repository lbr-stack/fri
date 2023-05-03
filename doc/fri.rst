FRI
===
This ``package`` integrates KUKA's Fast Robot Interface (FRI) into the ROS 2 ``ament_cmake`` build system. It leaves all source code untouched.

Robot Setup
-----------
.. note::
    Please also refer to :ref:`Additional Resources`.

Verify Connection to the Robot
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Turn on the robot (enable green power switch on the robot controller).
2. Connect your computer to the robot controller at ``X66`` (default IP: ``172.31.1.147``) via an ethernet cable.
3. Configure the same network on your computer, therefore, set your IP to ``172.31.1.148`` or similar.
4. Try ping the robot ``ping 172.31.1.147``, expect something like:

.. code-block:: bash
    
    PING 172.31.1.147 (172.31.1.147) 56(84) bytes of data.
    64 bytes from 172.31.1.147: icmp_seq=1 ttl=64 time=0.868 ms

Install Applications to the Robot
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Follow `Verify Connection to the Robot`_.
2. Install ``Sunrise Workbench`` on you computer (if you are part of King's download from :ref:`Additional Resources`).
3. Create a new project in ``Sunrise Workbench``:
   
    - ``File`` -> ``New`` -> ``Sunrise project``.
    - Leave the default IP ``172.31.1.147`` and click ``Next``.
    - Give your project a name, e.g. FRI and click ``Next``.
    - Select your robot, e.g. LBR Med 7 R800 and click ``Next``.
    - Select your Media Flange and click ``Next``.
    - Click ``Finish``. Select ``RoboticsAPI Application``, and press ``Next``.
    - Click ``Finish``.

4. lala


.. :ref:`LBR FRI ROS 2 Stack`
.. 5. 
.. 6. 
.. 7. , ``KONI`` (default IP: 192.170.10.2)

Writing your own ROS 2 Application
----------------------------------
.. note::
    If you intend to use the robot quickly, you can use the ``lbr_fri_ros2_stack`` (:ref:`LBR FRI ROS 2 Stack`), which is built on top of this package. 

If you intend to use the FRI in your own ROS 2 project, you can do so through the following:

- Add this repository to your workspace

.. code-block:: bash

    git clone https://github.com/KCL-BMEIS/fri.git -b ros2-fri-1.15

- In your ``package.xml`` add: 

.. code-block:: xml
    
    <depend>fri</depend>

- In your ``CMakeLists.txt`` add:

.. code-block:: cmake
    
    find_package(fri REQUIRED)

API
~~~
For the ``Doxygen`` generated API, checkout `fri <../../docs/doxygen/fri/html/hierarchy.html>`_.
