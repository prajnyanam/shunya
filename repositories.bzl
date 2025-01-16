

def load_git_repositories():
    git_repository(
        name = "example_repo",
        remote = "https://github.com/example/example-repo.git",
        branch = "main",  # or specify a commit instead
    )