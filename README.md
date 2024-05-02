<h1 align="center"> PHILOSOPHERS </h1>

<div align="center">
	<p>
		<a href="https://github.com/EvertonVaz/philosophers" target="_blank">
			<img height=170 src="https://game.42sp.org.br/static/assets/achievements/philosophersm.png" hspace = "10">
		</a>
	</p>

# [125/100]

</div>


# Desafio dos Filósofos: Sincronização em Sistemas Multithread

**Introdução**

Este repositório contém a implementação do clássico Desafio dos Filósofos, programado em C. O desafio simula um cenário onde um grupo de filósofos sentados em uma mesa redonda compartilham um prato de espaguete. Cada filósofo alterna entre três estados: comer, pensar e dormir. Para comer, porém, eles precisam de dois garfos, um à esquerda e outro à direita, mas cada filoso senta há mesa com apenas 1 garfo.

O problema surge quando pensamos na sincronização do acesso aos garfos. Se os filósofos não coordenarem bem a sua utilização, podemos cair em situações de impasse (deadlocks) onde cada filósofo fica eternamente segurando um garfo e esperando pelo outro, impossibilitando que qualquer um deles termine sua refeição.

**Parte Obrigatória (philo)**

A versão obrigatória utiliza threads e mutexes para sincronizar o acesso aos garfos. O programa pode ser compilado e executado usando o seguinte comando:

```
git clone https://github.com/EvertonVaz/philosophers.git && cd philosophers/philo
make
```

Para executar o programa com os seguintes parâmetros:

* 5 filósofos
* 10000 ms (10 segundos) de tempo para morrer
* 5000 ms (5 segundos) de tempo para comer
* 2000 ms (2 segundos) de tempo para dormir
* Cada filósofo precisa comer 2 vezes

use o seguinte comando:

```
./philo 5 10000 5000 2000 2
```

**Parte Bônus (philo_bonus)**

A versão bônus utiliza processos e semáforos para sincronização. O programa pode ser compilado e executado usando o seguinte comando:

```
cd /philo_bonus/
make
```

Para executar o programa com os mesmos parâmetros da parte obrigatória, use o seguinte comando:

```
./philo_bonus 5 10000 5000 2000 2
```
