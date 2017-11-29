1. Descargar modelo cinemático de gihub y compliar para ver que funcione.
2. Instalar paquetería de ROS llamada Gazebo.
3. Abrir una terminal en Ubuntu y poner los siguientes comandos:
	cd lentes
	cd EK_AutoNOMOS
	cd AutoNOMOS_simulation
	catkin_make
	source devel/setup.bash
	roslaunch autonomos_gazebo empty_autonomos.launch
4. En una nueva terminal:
	cd lentes
	cd proyecto
	catkin_make
5. Asignar x y theta esperadas.
6. Ir a Gazebo para ver el mvimiento.