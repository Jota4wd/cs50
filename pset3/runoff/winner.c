bool print_winner(void)
{
    int majority = voter_count / 2 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

/* Esta função verifica se algum candidato tem mais da metade dos votos. */
/* Calcula a maioria necessária (metade dos votos + 1). */
/* Verifica se algum candidato atingiu essa maioria. */
/* Se sim, imprime o nome do vencedor e retorna true. */
/* Se não, retorna false. */
