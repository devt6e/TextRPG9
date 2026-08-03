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
                # CP949(EUC-KR)로 해석해서 텍스트로 읽음
                $encodingCp949 = [System.Text.Encoding]::GetEncoding(949)
                $text = $encodingCp949.GetString($bytes)

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