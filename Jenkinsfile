pipeline {
    agent any
    environment {
        BUILD_DIR = "$WORKSPACE\\build"
    }

    stages {
        stage('Build') {
            agent {
                label 'windows && unreal-engine-4'
            }
            steps {
                echo 'Building..'
                bat(script: 'scripts\\jenkins-build.bat')
                echo 'Archiving...'
                archiveArtifacts(artifacts: '${env.BUILD_DIR}\\gamesense-plugin-ue4.zip')
            }
        }
    }
}
