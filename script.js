function toggleMenu() {
    const menu = document.querySelector(".menu-links");
    const icon = document.querySelector(".hamburger-icon");
    menu.classList.toggle("open");
    icon.classList.toggle("open");
}

// Funcionalidad para visualizar imágenes en alta resolución
document.addEventListener('DOMContentLoaded', function() {
    // Obtener el modal
    const modal = document.getElementById('imageModal');
    const modalImg = document.getElementById('modalImage');
    const closeBtn = document.getElementsByClassName('close')[0];
    const prevBtn = document.querySelector('.prev');
    const nextBtn = document.querySelector('.next');
    
    // Obtener todas las imágenes de la galería
    const galleryImages = document.querySelectorAll('.gallery-item img');
    let currentImageIndex = 0;
    let galleryArray = [];
    let currentGalleryContainer = null;
    
    // Crear un array con todas las imágenes de la galería actual
    function updateGalleryArray(clickedImage) {
        // Identificar la galería específica a la que pertenece la imagen en la que se hizo clic
        currentGalleryContainer = clickedImage.closest('.gallery-container');
        if (currentGalleryContainer) {
            galleryArray = Array.from(currentGalleryContainer.querySelectorAll('.gallery-item img'));
        }
    }
    
    // Añadir evento click a cada imagen
    galleryImages.forEach(img => {
        img.addEventListener('click', function() {
            updateGalleryArray(this);
            currentImageIndex = galleryArray.indexOf(this);
            openModal(this.src);
        });
    });
    
    // Función para abrir el modal
    function openModal(src) {
        modal.style.display = "block";
        modalImg.src = src;
    }
    
    // Función para navegar a la imagen anterior
    function showPrevImage() {
        if (galleryArray.length > 0) {
            currentImageIndex = (currentImageIndex - 1 + galleryArray.length) % galleryArray.length;
            modalImg.src = galleryArray[currentImageIndex].src;
        }
    }
    
    // Función para navegar a la siguiente imagen
    function showNextImage() {
        if (galleryArray.length > 0) {
            currentImageIndex = (currentImageIndex + 1) % galleryArray.length;
            modalImg.src = galleryArray[currentImageIndex].src;
        }
    }
    
    // Eventos para los botones de navegación
    prevBtn.addEventListener('click', showPrevImage);
    nextBtn.addEventListener('click', showNextImage);
    
    // Cerrar el modal al hacer clic en la X
    closeBtn.addEventListener('click', function() {
        modal.style.display = "none";
    });
    
    // Cerrar el modal al hacer clic fuera de la imagen
    modal.addEventListener('click', function(event) {
        if (event.target === modal) {
            modal.style.display = "none";
        }
    });
    
    // Manejar eventos de teclado
    document.addEventListener('keydown', function(event) {
        if (modal.style.display === "block") {
            if (event.key === "Escape") {
                modal.style.display = "none";
            } else if (event.key === "ArrowLeft") {
                showPrevImage();
            } else if (event.key === "ArrowRight") {
                showNextImage();
            }
        }
    });
});

