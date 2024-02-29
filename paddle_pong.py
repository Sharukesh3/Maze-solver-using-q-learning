import pygame
import sys
import time
import random

# Initialize Pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 1280,720
PADDLE_WIDTH, PADDLE_HEIGHT = 10, 60
BALL_RADIUS = 10
FPS = 60
WHITE = (0,255,255)
BLACK = (0, 0, 0)

# Set up the game window
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Paddle Pong Game")

# Set up the paddles and ball
player_paddle = pygame.Rect(50, HEIGHT // 2 - PADDLE_HEIGHT // 2, PADDLE_WIDTH, PADDLE_HEIGHT)
opponent_paddle = pygame.Rect(WIDTH - 50 - PADDLE_WIDTH, HEIGHT // 2 - PADDLE_HEIGHT // 2, PADDLE_WIDTH, PADDLE_HEIGHT)
ball = pygame.Rect(WIDTH // 2 - BALL_RADIUS // 2, HEIGHT // 2 - BALL_RADIUS // 2, BALL_RADIUS, BALL_RADIUS)

# Initialize ball speed
ball_speed = [random.choice([-4, 4]), random.choice([-4, 4])]  # Random initial speed

# Initialize scores
player_score = 0
opponent_score = 0
# AI power variables
opponent_ai_enabled = False
opponent_ai_power = 4  # Initial AI power level
min_ai_power = 3
max_ai_power = 5

# Fonts
font = pygame.font.Font(None, 36)

# Function to start a new round
def start_new_round():
    global opponent_ai_power

    # Randomly adjust AI power at the beginning of each round
    opponent_ai_power += random.choice([-1, 0, 1])
    opponent_ai_power = max(min_ai_power, min(opponent_ai_power, max_ai_power))

    time.sleep(1)  # Add a delay to slow down the ball at the start of a new round
    ball.x = WIDTH // 2 - BALL_RADIUS // 2
    ball.y = HEIGHT // 2 - BALL_RADIUS // 2
    ball_speed[0] = random.choice([-5, 5])  # Randomize initial ball direction
    ball_speed[1] = random.choice([-5, 5])

# Game loop
clock = pygame.time.Clock()
paused = False  # Flag to track if the game is paused

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        # Pause the game on spacebar press
        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            paused = not paused

        # Toggle AI control for the opponent paddle on 'A' key press
        if event.type == pygame.KEYDOWN and event.key == pygame.K_a:
            opponent_ai_enabled = not opponent_ai_enabled

    if not paused:
        # Move player paddle based on user input
        keys = pygame.key.get_pressed()
        if keys[pygame.K_w] and player_paddle.top > 0:
            player_paddle.y -= 5
        if keys[pygame.K_s] and player_paddle.bottom < HEIGHT:
            player_paddle.y += 5

        # Move opponent paddle (AI or user-controlled)
        if opponent_ai_enabled:
            if opponent_paddle.centery < ball.centery:
                opponent_paddle.y += opponent_ai_power
            elif opponent_paddle.centery > ball.centery:
                opponent_paddle.y -= opponent_ai_power
        else:
            if keys[pygame.K_UP] and opponent_paddle.top > 0:
                opponent_paddle.y -= 5
            if keys[pygame.K_DOWN] and opponent_paddle.bottom < HEIGHT:
                opponent_paddle.y += 5

        # Update ball position
        ball.x += ball_speed[0]
        ball.y += ball_speed[1]

        # Ball collision with walls
        if ball.top <= 0 or ball.bottom >= HEIGHT:
            ball_speed[1] = -ball_speed[1]

        # Ball collision with paddles
        if ball.colliderect(player_paddle):
            ball_speed[0] = abs(ball_speed[0])  # Change ball direction
        elif ball.colliderect(opponent_paddle):
            ball_speed[0] = -abs(ball_speed[0])  # Change ball direction

        # Ball missed by the opponent
        if ball.left <= 0:
            opponent_score += 1
            start_new_round()

        # Ball missed by the player
        if ball.right >= WIDTH:
            player_score += 1
            start_new_round()

    # Draw everything
    screen.fill(BLACK)
    pygame.draw.rect(screen, WHITE, player_paddle)
    pygame.draw.rect(screen, WHITE, opponent_paddle)

    # Change ball color
    pygame.draw.ellipse(screen, (255, 0, 0), ball)

    # Draw scores
    player_text = font.render(str(player_score), True, WHITE)
    opponent_text = font.render(str(opponent_score), True, WHITE)
    screen.blit(player_text, (WIDTH // 4, 20))
    screen.blit(opponent_text, (3 * WIDTH // 4 - player_text.get_width(), 20))

    # Draw pause text
    if paused:
        pause_text = font.render("Paused", True, WHITE)
        screen.blit(pause_text, (WIDTH // 2 - pause_text.get_width() // 2, HEIGHT // 2 - pause_text.get_height() // 2))

    # Draw AI control status
    ai_status_text = font.render("AI: " + ("On" if opponent_ai_enabled else "Off"), True, WHITE)
    screen.blit(ai_status_text, (WIDTH // 2 - ai_status_text.get_width() // 2, HEIGHT - 50))

    # Update the display
    pygame.display.flip()

    # Set the frame rate
    clock.tick(FPS)