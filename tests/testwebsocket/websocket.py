import asyncio
import websockets

# Set to store connected clients
connected_clients = set()

async def echo(websocket, path):
    # Register the new client
    connected_clients.add(websocket)
    print(f"Client connected: {websocket.remote_address}")

    try:
        async for message in websocket:
            print(f"Received from {websocket.remote_address}: {message}")
            await websocket.send(f"Echo: {message}")

            # Notify all clients about the new message
            for client in connected_clients:
                if client != websocket:  # Don't send the message back to the sender
                    await client.send(f"New message from {websocket.remote_address}: {message}")
    finally:
        # Unregister the client when it disconnects
        connected_clients.remove(websocket)
        print(f"Client disconnected: {websocket.remote_address}")

async def main():
    async with websockets.serve(echo, "localhost", 8765):
        print("WebSocket server is running on ws://localhost:8765")
        await asyncio.Future()  # Run forever

if __name__ == "__main__":
    asyncio.run(main())