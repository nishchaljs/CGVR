from github import Github

YOUR_GITHUB_TOKEN = os.environ['INPUT_SECRET']

g = Github(YOUR_GITHUB_TOKEN)

repo = g.get_repo("nishchaljs/CGVR")
pull_req_number = os.environ['INPUT_PULLREQ']
pull_request = repo.get_pull(number=pull_req_number)
commit = repo.get_commit(sha=pull_request.head.sha)

# Print the diff
diff_files = pull_request.get_files()
Files = []
for file in diff_files:
    Files.append(file.filename)
# Do further processing to get review comments, line_numbers, file_path
line_number = 18 
rev_lin = [["Use Python Version 2.7 instead", line_number, Files[0]]]

# Add a review comment to a specific file and line number
pull_request.create_review_comment(body=rev_lin[0][0], commit=commit, path=rev_lin[0][1], line=rev_lin[0][2])
