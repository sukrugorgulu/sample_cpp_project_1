pipeline {
    agent any
   
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh 'rm -rf ./build'
                sh 'mkdir ./build'
                sh 'cd ./build'
                sh 'cmake ..'
                sh 'make'
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
                sh 'mkdir -p ./files/bin'
                sh 'mkdir -p ./files/lib'
//                sh 'ldd ./curl-test | grep \"=> /\" | awk \'{print $3}\' | xargs -I '{}' cp -v \'{}\' ./files/lib'
                sh 'cp ./curl-test ./files/bin'
                sh 'tar -zcvf app-package.tar.gz ./files'
            }
        }
    }
}
