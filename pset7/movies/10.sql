SELECT DISTINCT pessoa.name FROM people AS pessoa JOIN directors AS diretor ON pessoa.id = diretor.person_id JOIN movies AS filme ON diretor.movie_id = filme.id JOIN ratings AS avaliacao ON filme.id = avaliacao.movie_id WHERE avaliacao.rating >= 9.0;

