pipeline {
    agent any

    stages {
        stage('Build') {
            agent {
                label 'windows && unreal-engine-4'
            }
            environment {
                BUILD_DIR = "$WORKSPACE\\build"
            }
            steps {
                echo 'Building..'
                bat(script: 'scripts\\jenkins-build.bat')
                echo 'Archiving...'
                archiveArtifacts(artifacts: "build\\gamesense-plugin-ue4.zip")
            }
        }
    }
}
