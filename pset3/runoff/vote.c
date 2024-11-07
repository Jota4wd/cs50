bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

/* Esta função registra a preferência de um votante para um determinado rank. */
/* Ela percorre todos os candidatos para encontrar o candidato com o nome fornecido. */
/* Se encontrar, registra o índice do candidato na matriz de preferências e retorna true. */
/* Se não encontrar nenhum candidato com esse nome, retorna false. */
