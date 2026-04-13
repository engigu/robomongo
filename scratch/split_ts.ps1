
$inputPath = "src/robomongo/resources/translations/robomongo_zh_CN.ts"
$outputDir = "src/robomongo/resources/translations"

$header = '<?xml version="1.0" encoding="utf-8"?>' + "`n" + '<!DOCTYPE TS>' + "`n" + '<TS version="2.1" language="zh_CN">'
$footer = '</TS>'

$content = Get-Content $inputPath -Raw
$contexts = [regex]::Matches($content, '(?s)<context>.*?</context>')

$core = @()
$gui = @()
$explorer = @()
$welcome = @()

foreach ($ctx in $contexts) {
    if ($ctx.Value -match '<name>Robomongo::WelcomeTab</name>') {
        $welcome += $ctx.Value
    }
    elseif ($ctx.Value -match '<name>Robomongo::Explorer') {
        $explorer += $ctx.Value
    }
    elseif ($ctx.Value -match '<name>Robomongo::(ConnectionSettings|MongoServer|SshTunnelTab|ConnectionBasicTab|ConnectionAuthTab|SSLTab|ConnectionAdvancedTab)</name>') {
        $core += $ctx.Value
    }
    else {
        $gui += $ctx.Value
    }
}

function Save-TS($name, $items) {
    $path = Join-Path $outputDir "robomongo_zh_CN_$name.ts"
    $full = $header + "`n" + ($items -join "`n") + "`n" + $footer
    [System.IO.File]::WriteAllText($path, $full, [System.Text.Encoding]::UTF8)
    Write-Host "Saved $path"
}

Save-TS "core" $core
Save-TS "gui" $gui
Save-TS "explorer" $explorer
Save-TS "welcome" $welcome
