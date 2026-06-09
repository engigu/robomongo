$runInfo = gh run list --workflow=build_mac.yml --limit 1 --json databaseId,status,conclusion | ConvertFrom-Json
if (-not $runInfo) {
    Write-Output "No run found."
    exit 1
}
$runInfo = $runInfo[0]
Write-Output "Run ID: $($runInfo.databaseId), Status: $($runInfo.status), Conclusion: $($runInfo.conclusion)"

if ($runInfo.status -eq "completed") {
    if ($runInfo.conclusion -eq "success") {
        Write-Output "Build SUCCESS"
        exit 0
    } else {
        Write-Output "Build FAILED. Fetching logs..."
        gh run view $runInfo.databaseId --log-failed
        exit 1
    }
} else {
    Write-Output "Build is still running..."
    exit 2
}
