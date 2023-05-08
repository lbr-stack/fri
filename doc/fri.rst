FRI
===
This ``package`` integrates KUKA's Fast Robot Interface (FRI) into the ROS 2 ``ament_cmake`` build system. It leaves all source code untouched.

Write your own ROS 2 Application
----------------------------------
.. note::
    If you intend to use the robot quickly, you can use the ``lbr_fri_ros2_stack`` (:ref:`LBR FRI ROS 2 Stack`), which is built on top of this package. 

If you intend to use the FRI in your own ROS 2 project, you can do so through the following:

- Add this repository to your workspace

.. code-block:: bash

    git clone https://github.com/KCL-BMEIS/fri.git -b ros2-fri-2.5

- In your ``package.xml`` add: 

.. code-block:: xml
    
    <depend>fri</depend>

- In your ``CMakeLists.txt`` add:

.. code-block:: cmake
    
    find_package(fri REQUIRED)

API
---
For the ``Doxygen`` generated API, checkout `fri <../../docs/doxygen/fri/html/hierarchy.html>`_.
