import {
  SubscribeMessage,
  WebSocketGateway,
  OnGatewayInit,
  WebSocketServer,
  OnGatewayConnection,
  OnGatewayDisconnect,
} from '@nestjs/websockets';
import { Injectable, Logger } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

@Injectable()
@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
export class MessageGateway
  implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect
{
  @WebSocketServer()
  server: Server;
  memory: Array<string> = [];

  private logger: Logger = new Logger('MessageGateway');

  @SubscribeMessage('msgToServer')
  async handleMessage(client: Socket, payload: string): Promise<void> {
    this.server.emit('msgToClient', payload);
    let len = 0;
    const a = (await prisma.comment.findMany({ select: { id: true } })).length;
    if (a > 0) {
      len = a;
    }
    await prisma.comment.create({
      data: {
        id: len,
        //@ts-ignore
        name: payload.name,
        //@ts-ignore
        text: payload.text,
      },
    });
  }

  afterInit(server: Server) {
    this.logger.log('Init');
  }

  handleDisconnect(client: Socket) {
    this.logger.log(`Client disconnected: ${client.id}`);
  }

  async handleConnection(client: Socket, ...args: any[]) {
    const comments = await prisma.comment.findMany({
      select: {
        id: true,
        name: true,
        text: true,
      },
    });
    for (let i = 0; i < comments.length; i++) {
      client.emit('msgToClient', {
        name: comments[i].name,
        text: comments[i].text,
      });
    }
    this.logger.log(`Client connected: ${client.id}`);
  }
}
