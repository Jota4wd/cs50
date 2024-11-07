SELECT pessoa.name FROM people pessoa JOIN stars elenco ON pessoa.id = elenco.person_id JOIN movies filme ON elenco.movie_id = filme.id WHERE filme.title = 'Toy Story';
