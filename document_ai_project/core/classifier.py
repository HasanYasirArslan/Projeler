# core/classifier.py

import requests

def classify_document(text: str) -> str:
    """
    Classify a document using the locally running Gemma3 model on Ollama.
    Returns one of: ID, Driving License, Job Application Form, Bill, Other
    """

    prompt = f"""
You are a document classification assistant.

Classify the following document into one of these categories:
- ID
- Driving License
- Job Application Form
- Bill
- Other

Only respond with the category name. No explanation.

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

    result = response.json()
    return result["response"].strip()
