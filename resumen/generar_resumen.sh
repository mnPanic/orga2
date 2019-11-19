#!/usr/bin/env bash

# Robado de lbarrios: https://github.com/lbarrios/algoritmos3-final/blob/master/resumen/generar_html.sh
# Con leves modificaciones

cat *.md >> junto.md
echo "Joined files"

#sed -i 's/[ ]*```/```/g' junto.md

markdown_py -q -o "html5" -c config.json -x markdown.extensions.toc -x markdown.extensions.tables -x markdown.extensions.fenced_code -x markdown.extensions.codehilite -x pymdownx.mark junto.md > junto.html
echo "Converted to html"

echo "
<!DOCTYPE html>
<html lang="en">
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta charset="utf-8">
	<link rel="stylesheet" type="text/css" href="./css/codehilite.css">
	<link rel="stylesheet" type="text/css" href="./css/github-markdown.css">
	<link rel="stylesheet" type="text/css" href="./css/custom.css">
	<style>
		.markdown-body {
			box-sizing: border-box;
			min-width: 200px;
			max-width: 980px;
			margin: 0 auto;
			padding: 45px;
		}

		@media (max-width: 767px) {
			.markdown-body {
				padding: 15px;
			}
		}
	</style>
</head>

<body>
	<article class="markdown-body">" > resumen.html

cat junto.html >> resumen.html

echo "</article>
</body></html>" >> resumen.html

echo "Cleanup"
rm -f junto.md junto.html