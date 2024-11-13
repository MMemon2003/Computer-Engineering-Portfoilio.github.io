// Function to show modules based on the year
function showModules(year) {
    // Hide all module year sections
    const years = document.querySelectorAll('.module-year');
    years.forEach(yearSection => yearSection.style.display = 'none');

    // Remove active class from all tab links
    const tabLinks = document.querySelectorAll('.tab-link');
    tabLinks.forEach(link => link.classList.remove('active'));

    // Show the clicked year and set active class
    document.getElementById(year).style.display = 'block';
    const activeTab = document.querySelector(`button[onclick="showModules('${year}')"]`);
    activeTab.classList.add('active');
}

// Smooth Scrolling for Anchor Links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function(e) {
        e.preventDefault();
        document.querySelector(this.getAttribute('href')).scrollIntoView({
            behavior: 'smooth'
        });
    });
});

// Toggle function to show and hide information
function toggleInfo(id) {
    const info = document.getElementById(id);
    info.style.display = info.style.display === 'none' || info.style.display === '' ? 'block' : 'none';
}

// Modal handling
function openModal(id) {
    document.getElementById(id).style.display = 'block';
    showSlide(0); // Initialize slideshow on open
}

function closeModal(id) {
    document.getElementById(id).style.display = 'none';
}

// Slideshow functionality
let currentSlide = 0;
function changeSlide(n) {
    showSlide(currentSlide += n);
}

function showSlide(n) {
    const slides = document.getElementsByClassName("slide");
    if (n >= slides.length) currentSlide = 0;
    if (n < 0) currentSlide = slides.length - 1;
    for (let i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";
    }
    slides[currentSlide].style.display = "block";
}

// Intersection Observer for animations on scroll
const observer = new IntersectionObserver(entries => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.classList.add('animate-slide-up');
        }
    });
});

document.querySelectorAll('.animate-slide-up').forEach(section => {
    observer.observe(section);
});

// Close modals when clicking outside
window.onclick = function(event) {
    const modals = document.getElementsByClassName('modal');
    for (let modal of modals) {
        if (event.target === modal) {
            modal.style.display = 'none';
        }
    }
};
