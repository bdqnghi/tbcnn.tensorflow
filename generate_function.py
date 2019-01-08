import os

fast = "docker run -v $(pwd):/e yijun/fast "
target_directory = "live_test/github_java/sort_function"


def generate_pb(src_path):
    path_splits = src_path.split(".")
   
  
    pb_path = os.path.join(path_splits[0] + ".pb")
    if not os.path.exists(pb_path):
        cmd = fast + src_path + " " + pb_path
        os.system(cmd)
    return pb_path


def generate_function_pb(pb_path):
    generate_function_pb_cmd = fast + "-A FUNCTION@NAME=.*sort.* " + pb_path
    os.system(generate_function_pb_cmd)

    path_splits = pb_path.split(".")

    function_pb_path = os.path.join(path_splits[0] + ".java-selected.pb")
    return function_pb_path
    

def generate_function_body_text(function_pb_path):
    path_splits = pb_path.split(".")
    function_body_path = path_splits[0] + "_function.java"

    generate_function_body_cmd = fast + function_pb_path + " " + function_body_path
    print(generate_function_body_cmd)
    os.system(generate_function_body_cmd)


for i in range(1, 11):
    algorithm_directory = os.path.join(target_directory,str(i))
    print(algorithm_directory)
    files = os.listdir(algorithm_directory)
    for file in files:
      
        file_path = os.path.join(algorithm_directory,file)
        path_splits = file_path.split("/")
        file_name = path_splits[len(path_splits)-1].split(".")[0]

        pb_path = generate_pb(file_path)
        
        function_pb_path = generate_function_pb(pb_path)

        generate_function_body_text(function_pb_path)