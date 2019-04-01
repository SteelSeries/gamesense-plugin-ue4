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
                dir('build') {
                    powershell('''
                        Write-Host Compressing build number: B${env:BUILD_NUMBER}
                        Get-ChildItem -Exclude Binaries, Intermediate, *.zip | `
                        Compress-Archive -Force -Verbose -CompressionLevel Fastest `
                        -DestinationPath "gamesense-plugin-ue4-B${env:BUILD_NUMBER}.zip"
                    ''')
                    archiveArtifacts(artifacts: "gamesense-plugin-ue4*.zip", fingerprint: true)
                }
            }
        }
    }
}
