FROM python:3.9-slim as flask

WORKDIR /app

COPY flask_app/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY flask_app/ .

CMD ["python", "app.py"]

FROM python:3.9-slim as lab

WORKDIR /app

COPY lab_app/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY lab_app/ .

CMD ["python", "app.py"]

FROM nginx:latest as final

COPY nginx/ /etc/nginx/  
