void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}
Explicação:

/* Esta função conta os votos para os candidatos não eliminados. */
/* Para cada votante, ela percorre suas preferências na ordem. */
/* Quando encontra o primeiro candidato não eliminado, incrementa o voto desse candidato e passa para o próximo votante. */
