import os
import json
from flask import Flask, render_template, url_for

app = Flask(__name__)

# --- CONFIGURAÇÃO ---
# A pasta ainda é necessária para servir os arquivos estáticos,
# mas não precisamos mais de lógica de gravação.
UPLOAD_FOLDER = 'static/uploads'
DATA_FILE = 'uploads_db.json'

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def load_uploads_db():
    """Lê o mapeamento de arquivos existente (se houver)."""
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, 'r') as f:
            try:
                return json.load(f)
            except json.JSONDecodeError:
                return {}
    return {}

# --- DADOS DA HISTÓRIA ---
STORY_PAGES = [
    {
        "title_pt": "A ORIGEM",
        "title_en": "THE ORIGIN",
        "chapter_pt": "Introdução",
        "chapter_en": "Intro",
        "content": {
            "text_pt": "Bem-vindo à lore oficial do presente de Amigo Secreto da Oryx Capital.",
            "text_en": "Welcome to the official lore of the Oryx Capital Secret Santa gift.",
            "subtext_pt": "Este gibi digital documenta a jornada caótica, técnica e sentimental para construir o presente do Anton. Do código C++ à solda manual, aqui está a prova de que a engenharia também é uma forma de afeto.",
            "subtext_en": "This digital comic documents the chaotic, technical, and sentimental journey to build Anton's gift. From C++ code to manual soldering, here is proof that engineering is also a form of affection.",
            "image_slots": 1,
            "image_labels_pt": ["Oryx Capital"],
            "image_labels_en": ["Oryx Capital Logo / Intro"]
        }
    },
    {
        "title_pt": "A MISSÃO: OPERAÇÃO ANTON",
        "title_en": "THE MISSION: OPERATION ANTON",
        "chapter_pt": "Capítulo 1",
        "chapter_en": "Chapter 1",
        "content": {
            "text_pt": "Tudo começou com o anúncio fatídico na Oryx Capital: O Amigo Secreto. O destino, com seu senso de humor peculiar, me sorteou Anton Ragin.",
            "text_en": "It all started with the fateful announcement at Oryx Capital: Secret Santa. Fate, with its peculiar sense of humor, assigned me Anton Ragin.",
            "subtext_pt": "Um russo-britânico, mestre dos códigos, amante de carros e matemática. Dar um presente comprado? Jamais! Seria uma ofensa à engenharia da sua mente. O objetivo era claro: criar algo totalmente personalizado, que desafiasse seu intelecto e honrasse sua paixão por tecnologia.",
            "subtext_en": "A Russian-British code master, car lover, and math enthusiast. Buying a gift? Never! It would be an insult to the engineering of his mind. The goal was clear: create something fully custom, challenging his intellect and honoring his passion for technology.",
            "image_slots": 1,
            "image_labels_pt": ["O Alvo: Anton Ragin"],
            "image_labels_en": ["The Target: Anton Ragin"]
        }
    },
    {
        "title_pt": "O CEMITÉRIO DE SILÍCIO",
        "title_en": "THE SILICON GRAVEYARD",
        "chapter_pt": "Capítulo 2",
        "chapter_en": "Chapter 2",
        "content": {
            "text_pt": "A primeira ideia parecia brilhante: um Raspberry Pi! O cérebro perfeito para um programador exigente como o Anton. Mas a realidade foi cruel...",
            "text_en": "The first idea seemed brilliant: a Raspberry Pi! The perfect brain for a demanding programmer like Anton. But reality was cruel...",
            "subtext_pt": "Ao abrir a gaveta de sucatas, encontrei apenas destroços. Pinos tortos, soldas frias e placas que viram dias melhores. Tentei reviver o velho Pi... com solda e esperança, mas o resultado foi um Frankenstein eletrônico que se recusava a viver. Abortar missão!",
            "subtext_en": "Opening the scrap drawer, I found only wreckage. Bent pins, cold solder joints, and boards that had seen better days. I tried to revive the old Pi... with solder and hope, but the result was an electronic Frankenstein that refused to live. Mission abort!",
            "image_slots": 2,
            "image_labels_pt": ["Raspberry Pi 'Morto'", "Tentativa falha de solda 🤢"],
            "image_labels_en": ["Dead Raspberry Pi", "Failed soldering attempt 🤢"]
        }
    },
    {
        "title_pt": "A GÊNESE DO ARDUINO",
        "title_en": "THE GENESIS OF ARDUINO",
        "chapter_pt": "Capítulo 3",
        "chapter_en": "Chapter 3",
        "content": {
            "text_pt": "EUREKA! Se o hardware pronto falhou, eu construiria o meu próprio ECOSSISTEMA. Sim, integração do presente entre website, arduino, programação... Não era apenas jogo, mas um desafio múltiplo!",
            "text_en": "EUREKA! If ready-made hardware failed, I would build my own ECOSYSTEM. Yes, integrating the gift between website, Arduino, programming... It wasn't just a game, but a multiple challenge!",
            "subtext_pt": "No mundo físico: Um Jogo da Memória impiedoso rodando em um Arduino UNO para ele treinar suas habilidades. No mundo digital: O código C++ seria o verdadeiro enigma. Easter Eggs escondidos na lógica, que ao serem achados, liberam funções no Arduino. O Code Review será necessário... DICA: Pressione o pino 12 quatro vezes e... A trilha sonora de 8-bits irá cantar!",
            "subtext_en": "In the physical world: A ruthless Memory Game running on an Arduino UNO to train his skills. In the digital world: The C++ code would be the true riddle. Easter Eggs hidden in the logic release functions on the Arduino. A Code Review will be necessary... HINT: Press pin 12 four times and... The 8-bit soundtrack will sing!",
            "image_slots": 3,
            "image_labels_pt": ["Esquema do Circuito", "Frankenstein quase vivo", "Easter Eggs do Mario"],
            "image_labels_en": ["Circuit Schematic", "Frankenstein almost alive", "Mario Easter Eggs"]
        }
    },
    {
        "title_pt": "A FORJA DE VULCANO",
        "title_en": "THE FORGE OF VULCAN",
        "chapter_pt": "Capítulo 4",
        "chapter_en": "Chapter 4",
        "content": {
            "text_pt": "O arsenal foi reunido: Resistores de 330Ω, Buzzers de 5V estridentes, Push Buttons táticos e LEDs vibrantes.",
            "text_en": "The arsenal was assembled: 330Ω Resistors, shrill 5V Buzzers, tactile Push Buttons, and vibrant LEDs.",
            "subtext_pt": "Mas faltava algo... a interface. Adicionei um módulo I2C e um display LCD 16x2 para dar uma 'cara' profissional ao monstro. O cheiro de estanho e chumbo preencheu o ar. Fio por fio, solda por solda, o emaranhado de cabos começou a ganhar forma e propósito.",
            "subtext_en": "But something was missing... the interface. I added an I2C module and a 16x2 LCD display to give the monster a professional 'face'. The smell of tin and lead filled the air. Wire by wire, solder by solder, the tangle of cables began to take shape and purpose.",
            "image_slots": 4,
            "image_labels_pt": ["O pingo de solda místico! ** AUMENTE O SOM ** ", "Soldando o LCD", "Montagem na Protoboard", "Componentes na Mesa"],
            "image_labels_en": ["The mystical solder blob! ** TURN ON THE SOUND **", "Soldering the LCD", "Breadboard assembly", "Components on the table"]
        }
    },
    {
        "title_pt": "O FANTASMA NA MÁQUINA",
        "title_en": "THE GHOST IN THE MACHINE",
        "chapter_pt": "Capítulo 5",
        "chapter_en": "Chapter 5",
        "content": {
            "text_pt": "Olhando para aquele LCD brilhando, tive uma epifania. Anton é a peça essencial no time, mas infelizmente, não é sempre que temos contato com ele. E se esse display falasse por nós?",
            "text_en": "Looking at that glowing LCD, I had an epiphany. Anton is an essential piece of the team, but unfortunately, we don't always have contact with him. What if this display spoke for us?",
            "subtext_pt": "O presente evoluiu. Não era mais só meu. Corri até a CEO e lancei a ideia: 'Vamos coletar frases de todos! Quero mostrar o carinho e dedicação da equipe inteira para o Anton'. O Arduino se tornou um mensageiro digital, exibindo o carinho e as boas-vindas de cada membro da Oryx, pixel por pixel.",
            "subtext_en": "The gift evolved. It wasn't just mine anymore. I ran to the CEO and pitched the idea: 'Let's collect phrases from everyone! I want to show the affection and dedication of the entire team to Anton'. The Arduino became a digital messenger, displaying the warmth and welcome of every Oryx member, pixel by pixel.",
            "image_slots": 3,
            "image_labels_pt": ["O LCD Funcionando", "Mensagens do Time", "O Código Compilando"],
            "image_labels_en": ["LCD Working", "Team Messages", "Code Compiling"]
        }
    },
    {
        "title_pt": "COMPILAÇÃO FINAL",
        "title_en": "FINAL COMPILATION",
        "chapter_pt": "Capítulo 6",
        "chapter_en": "Chapter 6",
        "content": {
            "text_pt": "Madrugada adentro. Café frio. Olhos vermelhos. O compilador C++ rodou sem erros. O buzzer tocou a melodia. Os LEDs piscaram em harmonia... Já sentia o gosto dos bits nesse momento.",
            "text_en": "Deep into the dawn. Cold coffee. Red eyes. The C++ compiler ran without errors. The buzzer played the melody. The LEDs blinked in harmony... I could taste the bits at this moment.",
            "subtext_pt": "Está vivo! Um ecossistema completo de hardware e software, feito à mão, com suor, solda e C++. Um presente único para um cara único. Missão cumprida, Oryx Capital!",
            "subtext_en": "It's alive! A complete ecosystem of hardware and software, handmade with sweat, solder, and C++. A unique gift for a unique guy. Mission accomplished, Oryx Capital!",
            "image_slots": 1,
            "image_labels_pt": ["O Presente Finalizado"],
            "image_labels_en": ["The Finished Gift"]
        }
    }
]

# --- ROTAS ---

@app.route('/')
def index():
    uploads = load_uploads_db()
    return render_template('index.html', pages=STORY_PAGES, uploads=uploads)

if __name__ == '__main__':
    app.run(debug=True)