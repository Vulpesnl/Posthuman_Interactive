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
    
    // Obtener todas las imágenes de la galería
    const galleryImages = document.querySelectorAll('.gallery-item img');
    
    // Añadir evento click a cada imagen
    galleryImages.forEach(img => {
        img.addEventListener('click', function() {
            modal.style.display = "block";
            modalImg.src = this.src;
        });
    });
    
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
    
    // Cerrar el modal con la tecla ESC
    document.addEventListener('keydown', function(event) {
        if (event.key === "Escape" && modal.style.display === "block") {
            modal.style.display = "none";
        }
    });
});

