bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}
Explicação:

/* Esta função verifica se há um empate entre todos os candidatos restantes. */
/* Percorre todos os candidatos não eliminados. */
/* Se encontrar algum candidato com número de votos diferente do mínimo, retorna false. */
/* Se todos os candidatos não eliminados tiverem o mesmo número de votos (min), retorna true. */
