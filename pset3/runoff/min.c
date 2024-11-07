int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}
Explicação:

/* Esta função encontra o menor número de votos entre os candidatos não eliminados. */
/* Inicializa min com o número total de votantes (maior valor possível). */
/* Percorre todos os candidatos não eliminados, atualizando min se encontrar um valor menor. */
/* Retorna o menor valor encontrado. */
