pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                rm -rf build
                mkdir build
                cd build
                cmake ..
                make
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
                mkdir -p ./files/bin
                mkdir -p ./files/lib
                ldd ./curl-test | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./files/lib
                cp ./curl-test ./files/bin
                tar -zcvf app-package.tar.gz ./files
            }
        }
    }
}