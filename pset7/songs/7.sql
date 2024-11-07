SELECT AVG(energy) as energia_media FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');
