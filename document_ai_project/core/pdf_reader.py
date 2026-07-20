import fitz  # PyMuPDF
from pdf2image import convert_from_path
import pytesseract
from PIL import Image
import tempfile
import os

def extract_text_from_pdf(pdf_path: str) -> str:
    """
    Extract text from a PDF file. Use OCR if it's a scanned image-based PDF.
    """
    text = ""
    is_text_found = False

    # Metin içeren sayfa varsa önce onu kullan
    doc = fitz.open(pdf_path)
    for page in doc:
        page_text = page.get_text().strip()
        if page_text:
            text += page_text + "\n"
            is_text_found = True

    if is_text_found:
        return text  # PyMuPDF başarılıysa OCR gerekmez

    # OCR gerekliyse pdf2image ile görsele çevir
    print("[INFO] No text found. Applying OCR...")

    with tempfile.TemporaryDirectory() as path:
        images = convert_from_path(pdf_path, output_folder=path)
        for img in images:
            ocr_text = pytesseract.image_to_string(img)
            text += ocr_text + "\n"

    return text.strip()
