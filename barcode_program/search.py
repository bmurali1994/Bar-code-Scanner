#anilkumarravuru
from splinter.browser import Browser
b=Browser()
database_url="http://gepir.gs1.org/v32/xx/gtin.aspx?Lang=en-US"
b.visit(database_url)
b.fill('TabContainerGTIN:TabPanelGTIN:txtRequestGTIN','k.ravuru')
b.find_by_type('submit').click()
f=open("barcode.txt","r+")
line=f.read()
while(not l==""):
	b.fill('TabContainerGTIN:TabPanelGTIN:txtRequestGTIN',line)
	b.find_by_type('submit').click()
	l=f.read()