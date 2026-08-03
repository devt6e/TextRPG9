# ConvertToUtf8.ps1
$targetFolders = @(".\src", ".\include")
$extensions = @("*.cpp", "*.h", "*.hpp")

foreach ($folder in $targetFolders) {
    Get-ChildItem -Path $folder -Recurse -Include $extensions | ForEach-Object {
        $filePath = $_.FullName

        # 원본 바이트 읽기
        $bytes = [System.IO.File]::ReadAllBytes($filePath)

        # 이미 UTF-8 BOM이 있는지 확인 (EF BB BF)
        $hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF

        if (-not $hasBom) {
            try {
                # BOM이 없어도 이미 UTF-8일 수 있으므로 먼저 엄격하게 검사한다.
                $utf8Strict = New-Object System.Text.UTF8Encoding($false, $true)
                try {
                    $text = $utf8Strict.GetString($bytes)
                } catch {
                    # 유효한 UTF-8이 아닐 때만 CP949로 해석한다.
                    $encodingCp949 = [System.Text.Encoding]::GetEncoding(949)
                    $text = $encodingCp949.GetString($bytes)
                }

                # UTF-8 BOM으로 다시 저장
                $utf8Bom = New-Object System.Text.UTF8Encoding($true)
                [System.IO.File]::WriteAllText($filePath, $text, $utf8Bom)

                Write-Host "변환됨: $filePath"
            } catch {
                Write-Host "실패: $filePath - $_"
            }
        } else {
            Write-Host "이미 UTF-8: $filePath"
        }
    }
}
