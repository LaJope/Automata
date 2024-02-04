from invoke import task
import os
import time


project_wd = os.getcwd()
project_name = project_wd.split('/')[-1].strip('.')


def setup_directory(c):
    c.run('mkdir -p Source_Files '
          '&& mkdir -p Header_Files '
          '&& echo "int main() {\n\treturn 0;\n}" '
          '> "./Source_Files/main.cpp"')


def clone_cmakelists(c):
    c.run('touch ~/.cmake-template/CMakeLists.txt')
    with open('/home/lajope/.cmake-template/CMakeLists.txt') as template:
        cmake_template = template.read().replace(
            'project_name', project_name)
        cmake_file = open(f'{project_wd}/CMakeLists.txt', 'x')
        cmake_file.write(cmake_template)
        cmake_file.close()


def clone_vcpkg(c):
    if (not os.path.isdir(f'{project_wd}/vcpkg')):
        c.run('git submodule add https://github.com/microsoft/vcpkg.git '
              '&& git submodule update --init '
              '&& cd vcpkg '
              '&& ./bootstrap-vcpkg.sh -disableMetrics '
              '&& cd ..')


def init_vcpkg(c):
    if (os.path.isdir(f'{project_wd}/vcpkg')):
        c.run(f'{project_wd}/vcpkg/bootstrap-vcpkg.sh')
        c.run(f'{project_wd}/vcpkg/vcpkg new --application')


@task
def cmakePrep(c, vcpkg=False, vcpkgOnly=False):
    if (not vcpkgOnly):
        setup_directory(c)
        clone_cmakelists(c)
    if (vcpkg or vcpkgOnly):
        clone_vcpkg(c)
        init_vcpkg(c)


def get_source_files_names(c):
    source_files = [
        f'./Source_Files/{file_name}'
        for file_name
        in os.listdir(f'{project_wd}/Source_Files/')
        if os.path.isfile(f'{project_wd}/Source_Files/{file_name}')
    ]
    return source_files


@task
def updateSrc(c):
    source_files = get_source_files_names(c)
    updated_source = f'set(SOURCE_FILES {" ".join(source_files)})\n'
    import fileinput
    for line in fileinput.input(f'{project_wd}/CMakeLists.txt', inplace=True):
        if line.startswith('set(SOURCE_FILES'):
            print(updated_source, end='')
        else:
            print(line, end='')


@task
def crun(c):
    c.run(f'{project_wd}/out/Debug/{project_name}')


# @task
# def tmuxcrun(c):
#     c.run('tmux send-keys -t 1 "cl && crun" Enter')


@task
# If you for some obscure reason discovered that, just ignore.
def tellMeTheTruth(c, name='Nikita'):
    print('Let me think.')
    time.sleep(4)
    print('Aha! I know something that you don\'t know!')
    time.sleep(2)
    print('Here comes the truth!')
    time.sleep(1)
    print('3')
    time.sleep(0.5)
    print('2')
    time.sleep(0.5)
    print('1')
    time.sleep(1)
    print(f'{name} loh. Trusi v goroh. Sel na lavochku i...\n'
          f'Оставшуюся часть речи Эмманюэля Маркона читайте в источнике.')


if __name__ == "__main__":
    print('This is a python invoke tasks file.\n'
          'To use these tasks, you need to install '
          'python invoke(through pip, apt-get or other)\n'
          'and run the command "invoke __task_name__"')
