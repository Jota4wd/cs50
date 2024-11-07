SELECT AVG(votes.rating) FROM ratings votes JOIN movies filmes ON votes.movie_id = filmes.id WHERE filmes.year = 2012;
