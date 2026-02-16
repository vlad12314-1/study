from sqlalchemy import create_engine

def get_connection():
    """
    Создает соединение с базой данных PostgreSQL
    """
    engine = create_engine(
        'postgresql+psycopg2://postgres:password@localhost:5432/task_manager_db'
    )
    return engine
