set -o errexit

bash ci/project/build.sh
bash ci/project/test.sh
bash ci/project/lint.sh
bash ci/release/push.sh
