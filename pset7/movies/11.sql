SELECT filme.title FROM movies AS filme JOIN stars AS elenco ON filme.id = elenco.movie_id JOIN people AS pessoa ON elenco.person_id = pessoa.id JOIN ratings AS avaliacao ON filme.id = avaliacao.movie_id WHERE pessoa.name = 'Chadwick Boseman' ORDER BY avaliacao.rating DESC LIMIT 5;