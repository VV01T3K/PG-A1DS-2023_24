# Fetch remote branches
git fetch origin

# Delete all local branches except main
git branch | grep -v "main" | xargs git branch -D

# Delete all remote branches except main
git branch -r | grep -v "main" | sed 's/origin\///' | xargs -I {} git push origin --delete {}


git fetch origin
git branch | grep -v "main" | xargs git branch -D
git branch -r | grep -v "main" | sed 's/origin\///' | xargs -I {} git push origin --delete {}