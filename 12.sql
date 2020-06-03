SELECT title FROM 
(SELECT title FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON people.id = stars.person_id
WHERE name = 'Johnny Depp'
INTERSECT
SELECT title FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON people.id = stars.person_id
WHERE name = 'Helena Bonham Carter');