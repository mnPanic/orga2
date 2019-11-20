#!/usr/bin/env bash

# Robado de lbarrios: https://github.com/lbarrios/algoritmos3-final/blob/master/resumen/generar_html.sh
# Con leves modificaciones

rm -f junto.md junto.html

for filename in *.md; do
	cat $filename >> junto.md
	cat <(echo) <(echo) >> junto.md
done

echo "Joined files"

#sed 's/[ ]*```/```/g' junto.md

markdown_py -q -o "html5" -c config.json -x mdx_truly_sane_lists -x markdown.extensions.toc -x markdown.extensions.tables -x markdown.extensions.fenced_code -x markdown.extensions.codehilite -x pymdownx.mark junto.md > junto.html
echo "Converted to html"

echo "
<!DOCTYPE html>
<html lang="en">
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<meta charset="utf-8">
	<link rel="stylesheet" type="text/css" href="./css/codehilite.css">
	<link rel="stylesheet" type="text/css" href="./css/github-markdown.css">
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

echo "Generated html"

wkhtmltopdf resumen.html resumen_orga2_systems_programming.pdf

echo "Converted to pdf"

echo "Cleanup"
rm -f junto.md junto.html