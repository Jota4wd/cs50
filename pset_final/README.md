# CS50 Final Project

# Gerenciador de Tarefas Simples
#### Descrição:
Este projeto é um **gerenciador de tarefas simples** que permite aos usuários adicionar, editar e gerenciar suas tarefas diárias. A aplicação é construída com **Python** e utiliza o framework **Flask** para o desenvolvimento web. Os dados das tarefas são armazenados em um banco de dados **SQLite** utilizando **SQLAlchemy** como ORM, facilitando a manipulação dos dados.

---

## Estrutura do Projeto

```plaintext
pset_final$ tree --prune -I 'venv'
.
├── app.py
├── instance
│   └── tasks.db
├── README.md
├── static
│   └── style.css
└── templates
    ├── 404.html
    ├── 500.html
    ├── add_task.html
    ├── edit_task.html
    ├── home.html
    ├── layout.html
    └── task_detail.html

**app.py: Este é o arquivo principal da aplicação, onde a lógica do **Flask é implementada.
**instance/tasks.db: O banco de dados **SQLite que armazena as tarefas.
**static/style.css: Arquivo **CSS para estilização da aplicação.
**templates: Contém os arquivos **HTML utilizados para renderizar as páginas da aplicação, incluindo:
**404.html: Página de erro 404.
**500.html: Página de erro 500.
**add_task.html: Formulário para adicionar novas tarefas.
**edit_task.html: Formulário para editar tarefas existentes.
**home.html: Página inicial que lista as tarefas.
**layout.html: Estrutura base para as páginas.
**task_detail.html: Detalhes de uma tarefa específica.

---

## Tecnologias do Projeto
[python, flask, sqlalchemy + sqlite]
**Python: Linguagem de programação utilizada.
**Flask: Framework web que permite o desenvolvimento rápido de aplicações.
**SQLAlchemy: ORM utilizado para interagir com o banco de dados SQLite.
**SQLite: Sistema de gerenciamento de banco de dados utilizado para armazenar as tarefas.

---

### Agradecimentos

I would like to thank David J. Malan, Brian, and everyone from the staff.
