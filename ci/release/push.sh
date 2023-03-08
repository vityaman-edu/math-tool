set -o errexit

bash ci/project/build.sh
bash ci/project/lint.sh

git status
git diff
git add -A
git commit -eF ci/release/message.txt
git push
