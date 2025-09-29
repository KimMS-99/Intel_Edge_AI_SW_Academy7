import os
from PIL import Image, ImageEnhance
import numpy as np
import random

def augment_image(img: Image.Image):
    augmented = []

    # 1. 원본 그대로
    #augmented.append(img)

    # 2. 반전
    augmented.append(img.transpose(Image.FLIP_LEFT_RIGHT))
    #augmented.append(img.transpose(Image.FLIP_TOP_BOTTOM))
    #augmented.append(img.transpose(Image.ROTATE_90))
    #augmented.append(img.transpose(Image.ROTATE_180))
    #augmented.append(img.transpose(Image.ROTATE_270))

    # 3. 회전 (±15, ±30, ±45) or (±10, ±20, ±30, ±40, ±50)
    for angle in [-15, 15, -30, 30, -45, 45]:
    #for angle in [-5, 5, -10, 10, -15, 15, -20, 20, -25, 25, -30, 30, -35, 35, -40, 40, -45, 45, -50, 50]:
        augmented.append(img.rotate(angle))

    # 4. 밝기 조정 (0.8x ~ 1.2x) or (0.6x ~ 1.4x)
    for factor in [0.8, 1.2]:
    #for factor in [0.6, 0.8, 1.2, 1.4]:
        enhancer = ImageEnhance.Brightness(img)
        augmented.append(enhancer.enhance(factor))

    # 5. 노이즈 추가
    arr = np.array(img)
    noise = np.random.randint(0, 20, arr.shape, dtype='uint8')
    noisy_img = Image.fromarray(np.clip(arr + noise, 0, 255).astype('uint8'))
    augmented.append(noisy_img)

    return augmented

def augment_folder(folder_path, output_count=1000):
    images = [f for f in os.listdir(folder_path) if f.lower().endswith(('.png', '.jpg', '.jpeg'))]
    os.makedirs(folder_path, exist_ok=True)

    total_augmented = 0
    for fname in images:
        img_path = os.path.join(folder_path, fname)
        img = Image.open(img_path).convert("L").resize((28, 28))

        augmented_images = augment_image(img)
        for i, aug_img in enumerate(augmented_images):
            aug_name = f"{os.path.splitext(fname)[0]}_aug_{i}.png"
            aug_path = os.path.join(folder_path, aug_name)
            aug_img.save(aug_path)
            total_augmented += 1

            if total_augmented >= output_count:
                print(f"✅ {total_augmented} augmented images saved.")
                return

    print(f"✅ Total augmented: {total_augmented}")

if __name__ == "__main__":
    data_path = "./dataset/train/marge_simpson/"
    augment_folder(data_path, output_count=200)

