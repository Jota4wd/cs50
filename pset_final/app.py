from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///tasks.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'sua_chave_secreta_aqui'
db = SQLAlchemy(app)

class Task(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    description = db.Column(db.Text, nullable=True)
    status = db.Column(db.String(20), nullable=False, default='Pendente')
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    updated_at = db.Column(db.DateTime, default=datetime.utcnow, onupdate=datetime.utcnow)

    def __repr__(self):
        return f'<Task {self.name}>'

    @property
    def status_class(self):
        status_classes = {
            'Pendente': 'warning',
            'Em Andamento': 'info',
            'Concluída': 'success',
            'Cancelada': 'danger'
        }
        return status_classes.get(self.status, 'secondary')

with app.app_context():
    db.create_all()
    
@app.route('/')
def home():
    search = request.args.get('search', '')
    status_filter = request.args.get('status', '')
    
    query = Task.query
    
    if search:
        query = query.filter(Task.name.contains(search))
    if status_filter:
        query = query.filter(Task.status == status_filter)
        
    tasks = query.order_by(Task.created_at.desc()).all()
    return render_template('home.html', 
                         tasks=tasks, 
                         search=search, 
                         status_filter=status_filter)

@app.route('/add', methods=['GET', 'POST'])
def add_task():
    if request.method == 'POST':
        try:
            task_name = request.form.get('task_name').strip()
            description = request.form.get('description', '').strip()
            
            if not task_name:
                flash('O nome da tarefa é obrigatório!', 'danger')
                return redirect(url_for('add_task'))
                
            new_task = Task(
                name=task_name,
                description=description,
                status='Pendente'
            )
            db.session.add(new_task)
            db.session.commit()
            flash('Tarefa adicionada com sucesso!', 'success')
            return redirect(url_for('home'))
            
        except Exception as e:
            db.session.rollback()
            flash(f'Erro ao adicionar tarefa: {str(e)}', 'danger')
            return redirect(url_for('add_task'))
            
    return render_template('add_task.html')

@app.route('/edit/<int:task_id>', methods=['GET', 'POST'])
def edit_task(task_id):
    task = Task.query.get_or_404(task_id)
    
    if request.method == 'POST':
        try:
            task_name = request.form.get('task_name').strip()
            
            if not task_name:
                flash('O nome da tarefa é obrigatório!', 'danger')
                return redirect(url_for('edit_task', task_id=task_id))
                
            task.name = task_name
            task.description = request.form.get('description', '').strip()
            task.status = request.form.get('status')
            db.session.commit()
            flash('Tarefa atualizada com sucesso!', 'success')
            return redirect(url_for('home'))
            
        except Exception as e:
            db.session.rollback()
            flash(f'Erro ao atualizar tarefa: {str(e)}', 'danger')
            return redirect(url_for('edit_task', task_id=task_id))
            
    return render_template('edit_task.html', task=task)

@app.route('/delete/<int:task_id>', methods=['POST'])
def delete_task(task_id):
    try:
        task = Task.query.get_or_404(task_id)
        db.session.delete(task)
        db.session.commit()
        flash('Tarefa excluída com sucesso!', 'success')
    except Exception as e:
        db.session.rollback()
        flash(f'Erro ao excluir tarefa: {str(e)}', 'danger')
    return redirect(url_for('home'))

@app.route('/task/<int:task_id>')
def task_detail(task_id):
    task = Task.query.get_or_404(task_id)
    return render_template('task_detail.html', task=task)

@app.route('/toggle_status/<int:task_id>')
def toggle_status(task_id):
    try:
        task = Task.query.get_or_404(task_id)
        if task.status == 'Pendente':
            task.status = 'Em Andamento'
        elif task.status == 'Em Andamento':
            task.status = 'Concluída'
        else:
            task.status = 'Pendente'
        db.session.commit()
        flash('Status atualizado com sucesso!', 'success')
    except Exception as e:
        db.session.rollback()
        flash(f'Erro ao atualizar status: {str(e)}', 'danger')
    return redirect(url_for('home'))

@app.errorhandler(404)
def not_found_error(error):
    return render_template('404.html'), 404

@app.errorhandler(500)
def internal_error(error):
    db.session.rollback()
    return render_template('500.html'), 500

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)