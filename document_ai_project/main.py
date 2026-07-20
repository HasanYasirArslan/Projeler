# main.py

from core.pdf_reader import extract_text_from_pdf
from core.classifier import classify_document
from core.extractor import extract_document_fields

pdf_path = "docs/sample6.pdf"

# 1. PDF'ten metni al
text = extract_text_from_pdf(pdf_path)

# 2. Belgeyi sınıflandır
category = classify_document(text)
print("Predicted Category:", category)

# 3. Sahip bilgisi çıkar
fields = extract_document_fields(text)
print("Extracted Fields:")
print(fields)
