# core/extractor.py

import requests
import json
import re

def extract_document_fields(text: str) -> dict:
    """
    Extract fields (full_name, address, date_of_birth, id_number) from document text
    using locally running Gemma3 model via Ollama.
    """

    prompt = f"""
You are a document understanding AI.

Extract the following fields from the document below:
- Full Name
- Address (if available)
- Date of Birth (format: YYYY-MM-DD if possible)
- ID Number (if available)

Return the result strictly in this JSON format:

{{
    "full_name": "",
    "address": "",
    "date_of_birth": "",
    "id_number": ""
}}

Only use the information provided. Do not make anything up.

Document:
{text[:3000]}
"""

    response = requests.post(
        "http://localhost:11434/api/generate",
        json={
            "model": "gemma3",
            "prompt": prompt,
            "stream": False
        }
    )

    result = response.json()["response"]

    # Kod bloğu varsa temizle
    cleaned = re.sub(r"```json|```", "", result).strip()

    try:
        return json.loads(cleaned)
    except Exception as e:
        print("⚠️ JSON parse hatası:", e)
        return {"raw": result}
