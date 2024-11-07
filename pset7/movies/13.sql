SELECT DISTINCT pessoa.name FROM people AS pessoa JOIN stars AS elenco ON pessoa.id = elenco.person_id JOIN movies AS filme ON elenco.movie_id = filme.id JOIN stars AS elenco_kb ON filme.id = elenco_kb.movie_id JOIN people AS kevin_bacon ON elenco_kb.person_id = kevin_bacon.id WHERE kevin_bacon.name = 'Kevin Bacon'   AND kevin_bacon.birth = 1958 AND pessoa.name != 'Kevin Bacon';
