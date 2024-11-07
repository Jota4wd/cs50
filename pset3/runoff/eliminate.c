void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
Explicação:

/* Esta função elimina todos os candidatos com o número mínimo de votos. */
/* Percorre todos os candidatos. */
/* Se um candidato não estiver eliminado e tiver o número mínimo de votos, marca-o como eliminado. */
