from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_node_list(context, *args, **kwargs):
    use_real_str = LaunchConfiguration('use_real').perform(context)
    use_real = use_real_str.lower()  == 'true'

    nodes = []

    # Filtro (sempre presenete)
    nodes.append(
        Node(
            package='sensor_filter',
            executable='telemetry_filter',
            name='telemetry_filter',
            parameters = [{ 'max_deviation': LaunchConfiguration('max_deviation') }]
        )
    )

    #Escolha do sensor
    if use_real:
        nodes.append(
            Node(
                package='sensor_comunication',
                executable='sensor_real',
                name='sensor_real',

            )
        )
    else:
        nodes.append(
            Node(
                package='sensor_comunication',
                executable='sensor_emulator',
                name='sensor_emulator'
            )
        )

    return nodes


def generate_launch_description():
    # a funcao generate_launch_description roda quando o pacote é construido, e define
    # os argumentos validos, entre outras coisas
    # Mas como é gerada na construcao do pacote, nao temos os valores passados para os argumentos

    use_real_desc = DeclareLaunchArgument(
        'use_real',
        default_value='false',
        description='Choose wether to use real or emulated sensor data'
    )

    max_deviation_desc = DeclareLaunchArgument(
        'max_deviation',
        default_value='2.0',
        description='Maximum deviation from mean for the filter to approve a message'
    )

    # para resolver esse problema, utilizamos a OpaqueFunction, que basicamente diz ao ros
    # quando for rodar o launcher com os paramentros definidos, rode a funcao dada para
    # decidir os nós rodados
    return LaunchDescription([
        use_real_desc,
        max_deviation_desc,
        # rode a funcao generate_node_list com as informacoes preenchidas para determinar os nós
        OpaqueFunction(function=generate_node_list)
    ])
