let currentPage = 0;
const pages = document.querySelectorAll('.comic-page');
const totalPages = pages.length;
let currentLang = 'pt'; // Estado inicial da linguagem

// Elementos da Interface
const progressBar = document.getElementById('scroll-progress');

// Elementos do Loading
const loadingOverlay = document.getElementById('loading-overlay');
const loadingText = document.getElementById('loading-text');
const loadingIcon = document.getElementById('loading-icon');
const loadingBar = document.getElementById('loading-bar');

// Temas de loading com traduções
const loadingThemes = [
    { text_pt: "TENTANDO SOLDAR...", text_en: "TRYING TO SOLDER...", color: "bg-gray-800", icon: '<i data-lucide="flame" class="w-20 h-20 text-orange-500"></i>', barColor: "bg-orange-500" },
    { text_pt: "CARREGANDO LADO SOMBRIO...", text_en: "LOADING DARK SIDE...", color: "bg-black", icon: '<i data-lucide="skull" class="w-20 h-20 text-red-600"></i>', barColor: "bg-red-600" },
    { text_pt: "COMPILANDO HARDWARE...", text_en: "COMPILING HARDWARE...", color: "bg-blue-900", icon: '<i data-lucide="hammer" class="w-20 h-20 text-yellow-400"></i>', barColor: "bg-yellow-400" },
    { text_pt: "FLASHANDO FIRMWARE...", text_en: "FLASHING FIRMWARE...", color: "bg-green-900", icon: '<i data-lucide="binary" class="w-20 h-20 text-green-400"></i>', barColor: "bg-green-400" },
    { text_pt: "IT'S A ME, MARIO!", text_en: "IT'S A ME, MARIO!", color: "bg-red-600", icon: '<i data-lucide="gamepad-2" class="w-20 h-20 text-white"></i>', barColor: "bg-white" }
];

updateUI();

// --- FUNÇÃO DE TROCA DE IDIOMA ---
function toggleLanguage() {
    currentLang = currentLang === 'pt' ? 'en' : 'pt';
    const body = document.body;
    body.setAttribute('data-lang', currentLang);

    const ptElements = document.querySelectorAll('.lang-pt');
    const enElements = document.querySelectorAll('.lang-en');

    if (currentLang === 'en') {
        ptElements.forEach(el => el.classList.add('hidden'));
        enElements.forEach(el => el.classList.remove('hidden'));
    } else {
        enElements.forEach(el => el.classList.add('hidden'));
        ptElements.forEach(el => el.classList.remove('hidden'));
    }
}

// --- FUNÇÕES DE ÁUDIO (ATMOSFERA) ---
function playZeldaMusic() {
    const audio = document.getElementById('zelda-theme');
    const video = document.getElementById('zelda-video-player');

    // Se a música tocar, queremos garantir que o vídeo esteja mudo para não ter conflito
    if (video) video.muted = true;

    if (audio) {
        if (!audio.paused) return;
        audio.volume = 0.5;
        audio.currentTime = 0;

        var playPromise = audio.play();

        if (playPromise !== undefined) {
            playPromise.then(_ => {
                console.log("Música iniciada automaticamente.");
            })
            .catch(error => {
                console.log("Autoplay bloqueado pelo navegador.", error);
            });
        }
    }
}

function pauseZeldaMusic() {
    const audio = document.getElementById('zelda-theme');
    if (audio) {
        audio.pause();
        audio.currentTime = 0;
    }
}

// --- NAVEGAÇÃO ---
function changePageWithDelay(direction) {
    const targetIndex = currentPage + direction;

    if (targetIndex < 0 || targetIndex >= totalPages) return;

    if (direction > 0) {
        const themeIndex = (targetIndex - 1) % loadingThemes.length;
        const theme = loadingThemes[targetIndex - 1] || loadingThemes[0];

        if (loadingOverlay) {
            loadingOverlay.className = `fixed inset-0 z-[100] flex flex-col items-center justify-center transition-opacity duration-300 ${theme.color}`;

            // Usa o texto baseado na língua atual
            loadingText.innerHTML = currentLang === 'en' ? theme.text_en : theme.text_pt;
            loadingIcon.innerHTML = theme.icon;

            if (window.lucide) lucide.createIcons();

            loadingOverlay.classList.remove('hidden');
            if(loadingBar) loadingBar.style.width = '0%';

            setTimeout(() => { if(loadingBar) loadingBar.style.width = '100%'; }, 50);

            setTimeout(() => {
                try {
                    executePageChange(direction);
                } catch (error) {
                    console.error("Erro na troca de página:", error);
                } finally {
                    loadingOverlay.classList.add('hidden');
                    if(loadingBar) loadingBar.style.width = '0%';
                }
            }, 2000);
        } else {
            executePageChange(direction);
        }
    } else {
        executePageChange(direction);
    }
}

function executePageChange(direction) {
    const newPage = currentPage + direction;

    if (newPage >= 0 && newPage < totalPages) {
        const currentEl = pages[currentPage];
        const nextEl = pages[newPage];

        if (currentEl) {
            currentEl.classList.remove('opacity-100', 'translate-x-0', 'scale-100', 'z-20');
            currentEl.classList.add('opacity-0', 'pointer-events-none');

            if (direction > 0) currentEl.classList.add('-translate-x-[100px]', 'scale-90');
            else currentEl.classList.add('translate-x-[100px]', 'scale-90');

            // Pausa vídeos da página anterior
            const vids = currentEl.querySelectorAll('video');
            vids.forEach(v => v.pause());
        }

        currentPage = newPage;

        // --- LÓGICA DE ÁUDIO POR PÁGINA ---
        // 4 = "A Forja de Vulcano"
        if (currentPage === 4) {
            playZeldaMusic();
        } else {
            pauseZeldaMusic();
        }

        if (nextEl) {
            nextEl.classList.remove('opacity-0', 'pointer-events-none', 'translate-x-[100px]', '-translate-x-[100px]', 'scale-90');
            nextEl.classList.add('opacity-100', 'translate-x-0', 'scale-100', 'z-20');
        }

        updateUI();
        const container = document.getElementById('pages-container');
        if(container) container.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
}

function updateUI() {
    if (progressBar) {
        const progress = ((currentPage + 1) / totalPages) * 100;
        progressBar.style.width = `${progress}%`;
    }
}

document.addEventListener('keydown', (e) => {
    if (e.key === 'ArrowRight') changePageWithDelay(1);
    if (e.key === 'ArrowLeft') changePageWithDelay(-1);
});