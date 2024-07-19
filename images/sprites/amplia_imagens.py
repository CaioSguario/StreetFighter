import os
from PIL import Image

def ampliar_imagem(imagem_caminho, fator):
    imagem = Image.open(imagem_caminho)
    largura, altura = imagem.size
    nova_largura = largura * fator
    nova_altura = altura * fator

    # Usar o algoritmo de interpolação Lanczos para melhor qualidade ao redimensionar
    imagem_ampliada = imagem.resize((nova_largura, nova_altura), Image.LANCZOS)
    
    return imagem_ampliada

def processar_diretorios(base_dir, fator):
    for root, dirs, files in os.walk(base_dir):
        for file in files:
            if file.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif')):
                caminho_completo = os.path.join(root, file)
                print(f'Ampliando imagem: {caminho_completo}')
                imagem_ampliada = ampliar_imagem(caminho_completo, fator)

                # Salva a imagem ampliada substituindo a original
                imagem_ampliada.save(caminho_completo)
                print(f'Imagem ampliada salva em: {caminho_completo}')

if __name__ == "__main__":
    base_dir = "."  # Diretório atual
    fator_ampliacao = 3
    processar_diretorios(base_dir, fator_ampliacao)

