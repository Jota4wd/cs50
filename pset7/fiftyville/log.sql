-- Keep a log of any SQL queries you execute as you solve the mystery.

-- listando todas as tabelas e esquemas no banco de dados para entender a estrutura
.tables
.schema

-- buscando relatórios de cena do crime na data e local do roubo
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Chamberlin Street';

-- nada foi retornado, procurando qualquer relatorio no dia mensionado
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- aparentemente a rua esta errada, procurando com as novas informaçoes
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- nenhuma novidade olhando as entrevistas que possam estar relacionadas ao crime na data do roubo
SELECT * FROM interviews WHERE month = 7 AND day = 28;

-- olhando os voos na data do crime
SELECT * FROM flights WHERE month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour, minute;

--buscando informaçoes para o primeiro voo do dia
SELECT voo.*, aeroporto.full_name AS destination_airport_name, aeroporto.city AS destination_city FROM flights voo JOIN airports aeroporto ON voo.destination_airport_id = aeroporto.id WHERE voo.id = 36;

-- descobrindo a cidade de destino do primeiro voo
SELECT city FROM airports WHERE full_name = 'LaGuardia Airport';

-- Verificando passageiros do voo 36
SELECT pessoa.name as nome, voo.destination_airport_id as destino, aeroporto.city as cidade FROM people pessoa JOIN passengers passageiro ON pessoa.passport_number = passageiro.passport_number JOIN flights voo ON passageiro.flight_id = voo.id JOIN airports aeroporto ON voo.destination_airport_id = aeroporto.id WHERE voo.id = 36;

-- seguindo pistas dos depoimentos e vendo oq eh possivel cruzar
--logs padaria
SELECT hour as hora, minute as minuto, activity as atividade, license_plate as placa FROM bakery_security_logs registro WHERE year = 2023 AND month = 7 AND day = 28 ORDER BY hora, minuto;

--logs transaçoes bancarias
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

--logs chamadas curtas
SELECT chamada.caller as numero_origem, chamada.receiver as numero_destino, chamada.duration as duracao, pessoa_origem.name as nome_origem, pessoa_destino.name as nome_destino FROM phone_calls chamada JOIN people pessoa_origem ON chamada.caller = pessoa_origem.phone_number JOIN people pessoa_destino ON chamada.receiver = pessoa_destino.phone_number WHERE chamada.year = 2023 AND chamada.month = 7 AND chamada.day = 28 AND chamada.duration < 60;

-- pessoas que fizeram saque no ATM
SELECT DISTINCT pessoa.name as nome, pessoa.phone_number as telefone, pessoa.license_plate as placa FROM people pessoa JOIN bank_accounts conta_bancaria ON pessoa.id = conta_bancaria.person_id JOIN atm_transactions transacao ON conta_bancaria.account_number = transacao.account_number WHERE transacao.year = 2023 AND transacao.month = 7 AND transacao.day = 28 AND transacao.atm_location = 'Leggett Street' AND transacao.transaction_type = 'withdraw';

--estou ficando maluco com tanto txt aberto para ir salvando os dados huahauhau
-- vamos combinar tudo agora cruzando informaçoes
-- Query combinando todas as pistas
SELECT DISTINCT pessoa.name as nome FROM people pessoa JOIN bank_accounts conta ON pessoa.id = conta.person_id JOIN atm_transactions transacao ON conta.account_number = transacao.account_number JOIN phone_calls chamada ON pessoa.phone_number = chamada.caller JOIN passengers passageiro ON pessoa.passport_number = passageiro.passport_number JOIN flights voo ON passageiro.flight_id = voo.id WHERE voo.id = 36 AND transacao.year = 2023 AND transacao.month = 7 AND transacao.day = 28 AND transacao.atm_location = 'Leggett Street' AND transacao.transaction_type = 'withdraw' AND chamada.year = 2023 AND chamada.month = 7 AND chamada.day = 28 AND chamada.duration < 60;

-- ultima verificaçao para descobrir o cumplice, pq dos 3 suspeitos 2 possuem alibis huahuahua
-- ligaçao do suspeito
SELECT DISTINCT pessoa.name as nome, pessoa.phone_number as telefone, pessoa.license_plate as placa, chamada.duration as duracao_chamada, pessoa_destino.name as nome_destino FROM people pessoa JOIN phone_calls chamada ON pessoa.phone_number = chamada.caller JOIN people pessoa_destino ON chamada.receiver = pessoa_destino.phone_number WHERE pessoa.name = 'Bruce' AND chamada.year = 2023 AND chamada.month = 7 AND chamada.day = 28 AND chamada.duration < 60;
