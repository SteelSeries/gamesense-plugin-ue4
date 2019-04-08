pipeline {
    agent any
    parameters {
        choice(name: 'UE_VERSION', choices: ['4.22', '4.21'], description: 'Unereal Engine 4 version that should be used to build the plugin.')
    }

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
                        -DestinationPath "gamesense-plugin-ue${env:UE_VERSION}-B${env:BUILD_NUMBER}.zip"
                    ''')
                    archiveArtifacts(artifacts: "gamesense-plugin-ue4*.zip", fingerprint: true)
                }
            }
        }
    }
}
