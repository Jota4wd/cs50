SELECT filmes.title, votes.rating FROM movies filmes JOIN ratings votes ON filmes.id = votes.movie_id WHERE filmes.year = 2010 ORDER BY votes.rating DESC, filmes.title ASC;
