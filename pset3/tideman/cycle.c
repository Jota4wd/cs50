bool creates_cycle(int winner, int loser)
{
    if (winner == loser)
        return true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
                return true;
        }
    }
    return false;
}
